package com.ilyabuglakov.triangleanalyzer.controller;

import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.ilyabuglakov.triangleanalyzer.application.exceptions.IllegalArgumentException;
import com.ilyabuglakov.triangleanalyzer.application.exceptions.InternalServerErrorException;
import com.ilyabuglakov.triangleanalyzer.model.AnalyzerRequestDto;
import com.ilyabuglakov.triangleanalyzer.model.AnalyzerResponseDto;
import com.ilyabuglakov.triangleanalyzer.model.Triangle;
import com.ilyabuglakov.triangleanalyzer.service.RequestCounter;
import com.ilyabuglakov.triangleanalyzer.service.TriangleAnalyzerService.ITriangleAnalyzerService;
import com.ilyabuglakov.triangleanalyzer.model.TriangleAttributes;
import com.ilyabuglakov.triangleanalyzer.service.TriangleCacher;
import com.ilyabuglakov.triangleanalyzer.service.Validator;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;

@RestController
@Controller
public class TriangleAnalyzerController{

    static final public Logger logger = LogManager.getLogger(TriangleAnalyzerController.class.getName());

    @Autowired
    ITriangleAnalyzerService service;
    @Autowired
    RequestCounter counter;
    @Autowired
    TriangleCacher<TriangleAttributes> cacher;

    @RequestMapping("/triangle-analyzer")
    public  ResponseEntity<?> analyzeTriangle(@RequestParam(value = "side1", required = true) int sd1,
                                              @RequestParam(value = "side2", required = true) int sd2,
                                              @RequestParam(value = "side3", required = true) int sd3)
    throws IllegalArgumentException, InternalServerErrorException   {
        return new ResponseEntity<>(formResponse(sd1, sd2, sd3), HttpStatus.OK);
    }

    private TriangleAttributes formResponse(int sd1, int sd2, int sd3){
        Validator.validate(sd1, sd2, sd3);
        counter.increment();
        logger.info("Normal work. Provided sides: side1={}, side2={}, side3={}", sd1, sd2, sd3);
        return useCache(sd1, sd2, sd3);
    }

    private TriangleAttributes useCache(int sd1, int sd2, int sd3){
        TriangleAttributes response = cacher.contains(sd1,sd2,sd3) ?
                                    cacher.get(sd1,sd2,sd3):
                                    cacher.put(sd1, sd2, sd3, service.formResponse(sd1, sd2, sd3));
        return response;
    }

    @RequestMapping("/request-count")
    public ResponseEntity<?> getCount(){
        return new ResponseEntity<>(counter.getValue(), HttpStatus.OK);
    }


    @PostMapping(value = "/triangle-analyzer-json")
    public ResponseEntity<?> triangleAnalyzerJson(@RequestBody Triangle t)
            throws JsonMappingException, JsonParseException, IOException, IllegalArgumentException {
        return new ResponseEntity<>(formResponse(t.getSide1(), t.getSide2(), t.getSide3()), HttpStatus.OK);
    }


    @PostMapping(value = "/triangle-analyzer-json-bulk", consumes = "application/json", produces = "application/json")
    public ResponseEntity<?> triangleAnalyzersJson(@RequestBody AnalyzerRequestDto triangles)
            throws JsonMappingException, JsonParseException, IOException, IllegalArgumentException {
        logger.info("Entered bulk method");
        return  new ResponseEntity<>(new AnalyzerResponseDto(
                triangles.getTrianglesList().stream().map(t -> {
                    return formResponse(t.getSide1(), t.getSide2(), t.getSide3());
        } ).collect(Collectors.toList())), HttpStatus.OK);
    }

}

