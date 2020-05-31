package com.ilyabuglakov.triangleanalyzer.service;

import com.ilyabuglakov.triangleanalyzer.service.analyzer.TriangleAnalyzerService;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;

import static org.junit.jupiter.api.Assertions.assertTrue;

public class TriangleAnalyzerServiceTest {

    private TriangleAnalyzerService triangleAnalyzerService;

    @BeforeMethod
    public void setup() {
        triangleAnalyzerService = new TriangleAnalyzerService();
    }

    @Test
    public void testIsEquilateral() {
        assertTrue(triangleAnalyzerService.isEquilateral(2, 2, 2));
    }

    @Test
    public void testIsIsosceles() {
        assertTrue(triangleAnalyzerService.isIsosceles(3, 2, 2));
    }

    @Test
    public void testIsRectangular() {
        assertTrue(triangleAnalyzerService.isRectangular(3, 4, 5));
    }
//
//    @Test
//    public void testValidation(){
//        assertTrue(triangleAnalyzerService.validate(4,5,6));
//    }
}
