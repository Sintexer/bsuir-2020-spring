package com.ilyabuglakov.triangleanalyzer.application.handlers;

import org.springframework.core.annotation.AnnotationUtils;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseStatus;

import javax.servlet.http.HttpServletRequest;

//@ControllerAdvice()
//class GlobalDefaultExceptionHandler {
//    public static final String DEFAULT_ERROR_VIEW = "error";
//
//    @ExceptionHandler(value = Exception.class)
//    public ResponseEntity<?>
//    defaultErrorHandler(HttpServletRequest req, Exception e) throws Exception {
//        if (AnnotationUtils.findAnnotation
//                (e.getClass(), ResponseStatus.class) != null)
//            throw e;
//
//        return ResponseEntity
//                .status(HttpStatus.BAD_REQUEST)
//                .contentType(MediaType.APPLICATION_JSON)
//                .body(String.format("{\"error\":\"%s\"}", e.getMessage()));
//    }
//}