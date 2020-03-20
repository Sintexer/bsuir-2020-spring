package com.ilyabuglakov.triangleanalyzer.application;

import com.ilyabuglakov.triangleanalyzer.controller.TriangleAnalyzerController;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

@RestControllerAdvice
public class InternalServerErrorExceptionHandler implements ExceptionMapper<InternalServerErrorException> {

    private String description;

    @Override
    @ExceptionHandler(InternalServerErrorException.class)
    public ResponseEntity<?> handle(InternalServerErrorException e) {
        description = e.getMessage()!=null? e.getMessage(): e.toString();
        TriangleAnalyzerController.logger.error(description);
        return ResponseEntity
                .status(HttpStatus.INTERNAL_SERVER_ERROR)
                .contentType(MediaType.APPLICATION_JSON)
                .body(String.format("{\"error\":\"%s\"}", description));
    }

}