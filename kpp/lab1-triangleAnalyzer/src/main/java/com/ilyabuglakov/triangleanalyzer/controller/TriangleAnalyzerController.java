package com.ilyabuglakov.triangleanalyzer.controller;

import com.ilyabuglakov.triangleanalyzer.service.TraceLogger;
import com.ilyabuglakov.triangleanalyzer.service.TriangleAnalyzerService;
import com.ilyabuglakov.triangleanalyzer.model.TriangleAnalyzer;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class TriangleAnalyzerController {
    @RequestMapping("/triangle-analyzer")
    public ResponseEntity<?> triangleAnalyzer(@RequestParam(value = "side1", required = true) String side1,
                                              @RequestParam(value = "side2", required = true) String side2,
                                              @RequestParam(value = "side3", required = true) String side3) {
        Integer sd1 = Integer.valueOf(side1), sd2 = Integer.valueOf(side2), sd3 = Integer.valueOf(side3);
        TriangleAnalyzerService service = new TriangleAnalyzerService();
        if (!service.isValid(sd1, sd2, sd3))
            throw new BadRequest();
        TraceLogger lg = new TraceLogger();
        lg.performSomeTask();
        return new ResponseEntity<>(new TriangleAnalyzer(service.isEquilateral(sd1, sd2, sd3),
                service.isIsosceles(sd1, sd2, sd3),
                service.isRectangular(sd1, sd2, sd3)), HttpStatus.OK);
    }
}

