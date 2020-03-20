package com.ilyabuglakov.triangleanalyzer.application;

import com.ilyabuglakov.triangleanalyzer.controller.TriangleAnalyzerController;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;



@RestControllerAdvice
public class IllegalArgumentExceptionHandler implements ExceptionMapper<IllegalArgumentException> {

    private String description;

    @Override
    @ExceptionHandler(IllegalArgumentException.class)
    public ResponseEntity<?> handle(IllegalArgumentException e) {
        description = e.getMessage()!=null? e.getMessage(): e.toString();
        TriangleAnalyzerController.logger.error(description);
        return ResponseEntity
                .status(HttpStatus.BAD_REQUEST)
                .contentType(MediaType.APPLICATION_JSON)
                .body(String.format("{\"error\":\"%s\"}", description));
    }
}

