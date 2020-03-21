package com.ilyabuglakov.triangleanalyzer.application.handlers;

import com.ilyabuglakov.triangleanalyzer.application.exceptions.InternalServerErrorException;
import com.ilyabuglakov.triangleanalyzer.controller.TriangleAnalyzerController;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

@RestControllerAdvice
public class InternalServerErrorExceptionHandler implements ExceptionMapper<InternalServerErrorException> {

    @Override
    @ExceptionHandler(InternalServerErrorException.class)
    public ResponseEntity<?> handle(InternalServerErrorException e) {
        String description = e.getMessage()!=null? e.getMessage(): "Internal server error";
        TriangleAnalyzerController.logger.error(description);
        return ResponseEntity
                .status(HttpStatus.INTERNAL_SERVER_ERROR)
                .contentType(MediaType.APPLICATION_JSON)
                .body(String.format("{\"error\":\"%s\"}", description));
    }

}