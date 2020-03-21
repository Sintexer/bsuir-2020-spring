package com.ilyabuglakov.triangleanalyzer.application;

import org.springframework.http.ResponseEntity;


public interface ExceptionMapper<T> {
    ResponseEntity<?> handle(T e);
}