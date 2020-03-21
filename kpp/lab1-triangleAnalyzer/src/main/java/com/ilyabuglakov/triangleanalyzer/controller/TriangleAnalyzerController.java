package com.ilyabuglakov.triangleanalyzer.controller;

import com.ilyabuglakov.triangleanalyzer.application.IllegalArgumentException;
import com.ilyabuglakov.triangleanalyzer.application.InternalServerErrorException;
import com.ilyabuglakov.triangleanalyzer.application.OperationNotImplementedException;
import com.ilyabuglakov.triangleanalyzer.service.TriangleAnalyzerService;
import com.ilyabuglakov.triangleanalyzer.model.TriangleAnalyzer;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class TriangleAnalyzerController {

    static final public Logger logger = LogManager.getLogger(TriangleAnalyzerController.class.getName());

    @RequestMapping("/triangle-analyzer")
    public ResponseEntity<?> triangleAnalyzer(@RequestParam(value = "side1", required = true) String side1,
                                              @RequestParam(value = "side2", required = true) String side2,
                                              @RequestParam(value = "side3", required = true) String side3) {
        Integer sd1 = Integer.valueOf(side1), sd2 = Integer.valueOf(side2), sd3 = Integer.valueOf(side3);
        TriangleAnalyzerService service = new TriangleAnalyzerService();

        //Triangle validation
        if (!service.validate(sd1, sd2, sd3)) {
            logger.error("Such triangle can't exist: side1={}, side2=, side3=", side1, side2, side3);
            throw new IllegalArgumentException();
        }

        //Check of InternalServerErrorExceptionHandler
        if (sd2 == 4) {
            logger.error("Server can't perform operation while side2=4");
            throw new InternalServerErrorException();
        }

        logger.info("Normal work. Provided sides: side1={}, side2={}, side3={}", side1, side2, side3);
        return new ResponseEntity<>(new TriangleAnalyzer(service.isEquilateral(sd1, sd2, sd3),
                service.isIsosceles(sd1, sd2, sd3),
                service.isRectangular(sd1, sd2, sd3)), HttpStatus.OK);
    }


    @RequestMapping("/insert")
    public ResponseEntity<?> insertTriangle() {
        logger.error("PUT request is in development");
        throw new OperationNotImplementedException();
    }
}

