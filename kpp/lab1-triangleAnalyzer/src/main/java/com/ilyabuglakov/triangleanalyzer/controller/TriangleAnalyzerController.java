package com.ilyabuglakov.triangleanalyzer.controller;

import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.ilyabuglakov.triangleanalyzer.application.exceptions.IllegalArgumentException;
import com.ilyabuglakov.triangleanalyzer.application.exceptions.InternalServerErrorException;
import com.ilyabuglakov.triangleanalyzer.model.Triangle;
import com.ilyabuglakov.triangleanalyzer.service.RequestCounter;
import com.ilyabuglakov.triangleanalyzer.service.TriangleAnalyzerService.ITriangleAnalyzerService;
import com.ilyabuglakov.triangleanalyzer.model.TriangleAnalyzer;
import com.ilyabuglakov.triangleanalyzer.service.TriangleCacher;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.RequestEntity;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMethod;

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
    TriangleCacher<TriangleAnalyzer> cacher;

    @RequestMapping("/triangle-analyzer")
    public ResponseEntity<?> triangleAnalyzer(@RequestParam(value = "side1", required = true) String side1,
                                              @RequestParam(value = "side2", required = true) String side2,
                                              @RequestParam(value = "side3", required = true) String side3)
    throws IllegalArgumentException, InternalServerErrorException   {
        Integer sd1 = Integer.valueOf(side1), sd2 = Integer.valueOf(side2), sd3 = Integer.valueOf(side3);

        //Triangle validation
        validationHelper(sd1, sd2, sd3);

        counter.increment();
        TriangleAnalyzer response = responseHelper(sd1, sd2, sd3);

        logger.info("Normal work. Provided sides: side1={}, side2={}, side3={}", side1, side2, side3);
        return new ResponseEntity<>(response, HttpStatus.OK);
    }

    private void validationHelper(int sd1, int sd2, int sd3)
    throws IllegalArgumentException{
        if (!service.validate(sd1, sd2, sd3)) {
            throw new IllegalArgumentException(
                    String.format("Provided sides can't form a triangle:" +
                                    " side1=%d, side2=%d, side3=%d", sd1, sd2, sd3));
        }
    }

    private TriangleAnalyzer responseHelper(int sd1, int sd2, int sd3){
        TriangleAnalyzer response = cacher.contains(sd1,sd2,sd3) ?
                                    cacher.get(sd1,sd2,sd3):
                                    cacher.put(sd1, sd2, sd3, service.formResponse(sd1, sd2, sd3));
        return response;
    }

    @RequestMapping("/request-count")
    public ResponseEntity<?> getCount(){
        return new ResponseEntity<>(counter.getValue(), HttpStatus.OK);
    }

    @RequestMapping(value = "/triangle-analyzer-json", method = RequestMethod.GET)
    public ResponseEntity<?> triangleAnalyzerJson(@RequestBody String triangle_analyzer_json)
    throws JsonMappingException, JsonParseException, IOException, IllegalArgumentException {
        Triangle triangle = new ObjectMapper().readValue(triangle_analyzer_json, Triangle.class);
        validationHelper(triangle.getSide1(), triangle.getSide2(), triangle.getSide3());
        TriangleAnalyzer response = responseHelper(triangle.getSide1(), triangle.getSide2(), triangle.getSide3());
        logger.info("Normal work. Provided in JSON sides: side1={}, side2={}, side3={}",
                triangle.getSide1(), triangle.getSide2(), triangle.getSide3());
        return new ResponseEntity<>(response, HttpStatus.OK);
    }

    @RequestMapping(value = "/triangle-analyzer-json-bulk", method = RequestMethod.GET)
    public List<ResponseEntity<?>> triangleAnalyzersJson(@RequestBody String triangle_analyzers_json)
            throws JsonMappingException, JsonParseException, IOException, IllegalArgumentException {
        return  new ObjectMapper().readValue(triangle_analyzers_json, new TypeReference<List<Triangle>>() {}).
                stream().map(t -> {
                    validationHelper(t.getSide1(),t.getSide2(),t.getSide3());
                    return new ResponseEntity<>(responseHelper(t.getSide1(),t.getSide2(),t.getSide3()), HttpStatus.OK);
        } ).collect(Collectors.toList());
    }

}

