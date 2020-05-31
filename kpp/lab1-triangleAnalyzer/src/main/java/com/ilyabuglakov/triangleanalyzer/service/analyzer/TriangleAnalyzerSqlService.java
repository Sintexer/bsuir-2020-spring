package com.ilyabuglakov.triangleanalyzer.service.analyzer;

import com.ilyabuglakov.triangleanalyzer.entity.*;
import com.ilyabuglakov.triangleanalyzer.model.*;
import com.ilyabuglakov.triangleanalyzer.repository.ProcessIdRepository;
import com.ilyabuglakov.triangleanalyzer.repository.StatisticRepository;
import com.ilyabuglakov.triangleanalyzer.repository.TriangleAttributesRepository;
import com.ilyabuglakov.triangleanalyzer.repository.TriangleRepository;
import com.ilyabuglakov.triangleanalyzer.service.RequestCounter;
import com.ilyabuglakov.triangleanalyzer.service.converter.TriangleConverter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

@Service
public class TriangleAnalyzerSqlService {

    @Autowired
    TriangleAnalyzerService service;
    @Autowired
    RequestCounter counter;
    @Autowired
    ProcessIdRepository processIdRepository;
    @Autowired
    StatisticRepository statisticRepository;
    @Autowired
    TriangleAttributesRepository triangleAttributesRepository;
    @Autowired
    TriangleRepository triangleRepository;

    public Long formResponse(List<Triangle> triangles){
        counter.increment();
        Long processId = generateProcessId();
        processIdRepository.save(new ProcessIdEntity(processId, ProcessStatus.PROCESSING.toString()));
        processTriangles(processId, triangles);
        return processId;
    }

    public ResponseEntity<?> formResponse(Long processId){
        if(processIdRepository.findByProcessId(processId).getStatus().equals(ProcessStatus.READY.toString())) {
            AnalyzerResponseDtoBuilder dtoBuilder = new AnalyzerResponseDtoBuilder();
            TriangleAttributesBuilder trb = new TriangleAttributesBuilder();
            StatisticEntity statistic = statisticRepository.findByProcessId(processId);
            dtoBuilder.setInvalidRequestCount(statistic.getInvalidRequestCount());
            dtoBuilder.setTotalRequestsCount(statistic.getTotalRequestsCount());
            dtoBuilder.setUniqueRequestCount(statistic.getUniqueRequestCount());
            dtoBuilder.setResponseList(triangleAttributesRepository.findAllByProcessId(processId).stream().map(te -> {
                trb.reset();
                trb.setEquilateral(te.isEquilateral());
                trb.setIsosceles(te.isIsosceles());
                trb.setRectangular(te.isRectangular());
                trb.setTriangle(new Triangle(te.getSide1(), te.getSide2(), te.getSide3()));
                return trb.build();
            }).collect(Collectors.toList()));
            return ResponseEntity.ok(dtoBuilder.build());
        }
        return new ResponseEntity("Still processing",HttpStatus.NO_CONTENT);
    }

    private void processTriangles(Long processId, List<Triangle> triangles){
        AnalyzerResponseDto response = service.formResponse(triangles);
        response.getResponseList().forEach(t -> {
            triangleRepository.save(new TriangleEntity(processId, t.getTriangle()));
            triangleAttributesRepository.save(new TriangleAttributesEntity(processId, t));
        });
        statisticRepository.save(new StatisticEntity(processId, response.getTotalRequestsCount(), response.getUniqueRequestCount(), response.getInvalidRequestCount()));
        ProcessIdEntity pidEntity = processIdRepository.findByProcessId(processId);
        pidEntity.setStatus(ProcessStatus.READY.toString());
        processIdRepository.save(pidEntity);
    }

    private Long generateProcessId(){
        Random random = new Random();
        Long processId;
        do{
            processId = random.nextLong();
        } while(processIdRepository.existsByProcessId(processId));
        return processId;
    }

    private boolean triangleExists(Triangle t){
        return triangleRepository.existsBySide1AndSide2AndSide3(t.getSide1(), t.getSide2(), t.getSide3());
    }
}
