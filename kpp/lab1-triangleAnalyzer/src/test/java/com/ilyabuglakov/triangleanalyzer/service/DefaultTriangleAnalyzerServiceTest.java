package com.ilyabuglakov.triangleanalyzer.service;

import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;

import static org.junit.jupiter.api.Assertions.assertTrue;

public class DefaultTriangleAnalyzerServiceTest {

    private DefaultTriangleAnalyzerService defaultTriangleAnalyzerService;

    @BeforeMethod
    public void setup() {
        defaultTriangleAnalyzerService = new DefaultTriangleAnalyzerService();
    }

    @Test
    public void testIsEquilateral() {
        assertTrue(defaultTriangleAnalyzerService.isEquilateral(2, 2, 2));
    }

    @Test
    public void testIsIsosceles() {
        assertTrue(defaultTriangleAnalyzerService.isIsosceles(3, 2, 2));
    }

    @Test
    public void testIsRectangular() {
        assertTrue(defaultTriangleAnalyzerService.isRectangular(3, 4, 5));
    }

    @Test
    public void testValidation(){
        assertTrue(defaultTriangleAnalyzerService.validate(4,5,6));
    }
}
