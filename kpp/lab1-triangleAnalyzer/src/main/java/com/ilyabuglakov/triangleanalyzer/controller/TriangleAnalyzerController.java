package com.ilyabuglakov.triangleanalyzer.controller;

import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.ilyabuglakov.triangleanalyzer.application.exceptions.IllegalArgumentException;
import com.ilyabuglakov.triangleanalyzer.application.exceptions.InternalServerErrorException;
import com.ilyabuglakov.triangleanalyzer.entity.TriangleEntity;
import com.ilyabuglakov.triangleanalyzer.model.*;
import com.ilyabuglakov.triangleanalyzer.repository.TriangleAttributesRepository;
import com.ilyabuglakov.triangleanalyzer.repository.TriangleRepository;
import com.ilyabuglakov.triangleanalyzer.service.analyzer.TriangleAnalyzerService;
import com.ilyabuglakov.triangleanalyzer.service.analyzer.TriangleAnalyzerSqlService;
import com.ilyabuglakov.triangleanalyzer.service.converter.TriangleConverter;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;


import java.io.IOException;

@RestController
@Controller
public class TriangleAnalyzerController{

    static final public Logger logger = LogManager.getLogger(TriangleAnalyzerController.class.getName());

    @Autowired
    TriangleAnalyzerService service;
    @Autowired
    TriangleAnalyzerSqlService sqlService;
    @Autowired
    TriangleAttributesRepository triangleAttributesRepository;


    @RequestMapping("/triangle-analyzer")
    public  ResponseEntity<?> analyzeTriangle(@RequestParam(value = "side1", required = true) int sd1,
                                              @RequestParam(value = "side2", required = true) int sd2,
                                              @RequestParam(value = "side3", required = true) int sd3)
    throws IllegalArgumentException, InternalServerErrorException   {
        return ResponseEntity.ok(service.formResponse(sd1, sd2, sd3));
    }


    @RequestMapping("/request-count")
    public ResponseEntity<?> getCount(){
        return ResponseEntity.ok(service.getCounterValue());
    }


    @PostMapping(value = "/triangle-analyzer-json")
    public ResponseEntity<?> triangleAnalyzerJson(@RequestBody Triangle t)
            throws JsonMappingException, JsonParseException, IOException, IllegalArgumentException {
        return ResponseEntity.ok(service.formResponse(t.getSide1(), t.getSide2(), t.getSide3()));
    }


    @PostMapping(value = "/triangle-analyzer-json-bulk", consumes = "application/json")
    public ResponseEntity<?> triangleAnalyzersJson(@RequestBody AnalyzerRequestDto triangles)
            throws JsonMappingException, JsonParseException, IOException, IllegalArgumentException {
        return  ResponseEntity.ok(service.formResponse(triangles.getTriangles()));
    }

    @PostMapping(value = "/triangle-analyzer-sql", consumes = "application/json")
    public ResponseEntity<?> triangleAnalyzerSql(@RequestBody AnalyzerRequestDto triangles){
        return ResponseEntity.ok(sqlService.formResponse(triangles.getTriangles()));
    }

    @GetMapping(value = "/triangle-analyzer-sql/{processId}")
    public ResponseEntity<?> triangleAnalyzerSqlGet(@PathVariable Long processId){
        return sqlService.formResponse(processId);
    }
}

