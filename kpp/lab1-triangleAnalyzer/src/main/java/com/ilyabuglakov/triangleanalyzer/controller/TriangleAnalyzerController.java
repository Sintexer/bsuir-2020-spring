package com.ilyabuglakov.triangleanalyzer.controller;

import com.ilyabuglakov.triangleanalyzer.application.exceptions.IllegalArgumentException;
import com.ilyabuglakov.triangleanalyzer.application.exceptions.InternalServerErrorException;
import com.ilyabuglakov.triangleanalyzer.service.RequestCounter;
import com.ilyabuglakov.triangleanalyzer.service.TriangleAnalyzerService.ITriangleAnalyzerService;
import com.ilyabuglakov.triangleanalyzer.model.TriangleAnalyzer;
import com.ilyabuglakov.triangleanalyzer.service.TriangleCacher;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

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
        if (!service.validate(sd1, sd2, sd3)) {
            throw new IllegalArgumentException(
                    String.format("Provided sides can't form a triangle:" +
                            " side1=%s, side2=%s, side3=%s",
                            side1, side2, side3));
        }

        counter.increment();
        TriangleAnalyzer response;
        response = cacher.contains(side1,side2,side3) ?
                cacher.get(side1,side2,side3):
                cacher.put(side1, side2, side3, service.formResponse(sd1, sd2, sd3));

        logger.info("Normal work. Provided sides: side1={}, side2={}, side3={}", side1, side2, side3);
        return new ResponseEntity<>(response, HttpStatus.OK);
    }

    @RequestMapping("/request-count")
    public ResponseEntity<?> getCount(){
        return new ResponseEntity<>(counter.getValue(), HttpStatus.OK);
    }

}

