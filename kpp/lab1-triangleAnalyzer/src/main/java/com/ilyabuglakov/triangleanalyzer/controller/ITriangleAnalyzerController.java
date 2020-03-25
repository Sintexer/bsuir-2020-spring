package com.ilyabuglakov.triangleanalyzer.controller;

import org.springframework.http.ResponseEntity;

public interface ITriangleAnalyzerController {
    public ResponseEntity<?> triangleAnalyzer(String side1, String side2, String side3);
}
