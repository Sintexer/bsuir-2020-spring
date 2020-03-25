package com.ilyabuglakov.triangleanalyzer.application.handlers;

import com.ilyabuglakov.triangleanalyzer.application.exceptions.IllegalArgumentException;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;



@RestControllerAdvice
public class IllegalArgumentExceptionHandler implements ExceptionMapper<IllegalArgumentException> {
    private static Logger logger = LogManager.getLogger(IllegalArgumentExceptionHandler.class);
    @Override
    @ExceptionHandler(IllegalArgumentException.class)
    public ResponseEntity<?> handle(IllegalArgumentException e) {
        logger.error(e.getMessage());
        return ResponseEntity
                .status(HttpStatus.BAD_REQUEST)
                .contentType(MediaType.APPLICATION_JSON)
                .body(String.format("{\"error\":\"%s\"}", e.getMessage()));
    }
}

