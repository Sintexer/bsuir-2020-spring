package com.ilyabuglakov.triangleanalyzer.application;

import com.ilyabuglakov.triangleanalyzer.controller.TriangleAnalyzerController;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;


public interface ExceptionMapper<T> {
    ResponseEntity<?> handle(T e);
}