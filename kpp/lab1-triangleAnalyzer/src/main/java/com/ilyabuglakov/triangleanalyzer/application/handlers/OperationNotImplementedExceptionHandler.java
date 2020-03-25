package com.ilyabuglakov.triangleanalyzer.application.handlers;

import com.ilyabuglakov.triangleanalyzer.application.exceptions.OperationNotImplementedException;
import com.ilyabuglakov.triangleanalyzer.controller.TriangleAnalyzerController;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;



@RestControllerAdvice
public class OperationNotImplementedExceptionHandler implements ExceptionMapper<OperationNotImplementedException> {

    private static Logger logger = LogManager.getLogger(OperationNotImplementedExceptionHandler.class);

    @Override
    @ExceptionHandler(OperationNotImplementedException.class)
    public ResponseEntity<?> handle(OperationNotImplementedException e) {
        logger.error(e.getMessage());
        return ResponseEntity
                .status(HttpStatus.INTERNAL_SERVER_ERROR)
                .contentType(MediaType.APPLICATION_JSON)
                .body(String.format("{\"error\":\"%s\"}", e.getMessage()));
    }

}