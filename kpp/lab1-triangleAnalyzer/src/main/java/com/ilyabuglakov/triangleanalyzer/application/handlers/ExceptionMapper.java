package com.ilyabuglakov.triangleanalyzer.application.handlers;

import org.springframework.http.ResponseEntity;

public interface  ExceptionMapper<T> {
        ResponseEntity<?> handle(T e);
}
