package com.ilyabuglakov.triangleanalyzer.application;

import com.ilyabuglakov.triangleanalyzer.controller.TriangleAnalyzerController;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;



@RestControllerAdvice
public class OperationNotImplementedExceptionHandler implements ExceptionMapper<OperationNotImplementedException> {

    @Override
    @ExceptionHandler(OperationNotImplementedException.class)
    public ResponseEntity<?> handle(OperationNotImplementedException e) {
        String description = e.getMessage()!=null? e.getMessage(): "Operation is not implemented";
        TriangleAnalyzerController.logger.error(description);
        return ResponseEntity
                .status(HttpStatus.INTERNAL_SERVER_ERROR)
                .contentType(MediaType.APPLICATION_JSON)
                .body(String.format("{\"error\":\"%s\"}", description));
    }

}