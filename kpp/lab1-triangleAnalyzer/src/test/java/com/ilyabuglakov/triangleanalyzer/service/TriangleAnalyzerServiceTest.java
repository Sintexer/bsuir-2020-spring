package com.ilyabuglakov.triangleanalyzer.service;


import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.junit4.SpringRunner;

import static org.junit.Assert.*;

@RunWith(SpringRunner.class)
public class TriangleAnalyzerServiceTest {

    private TriangleAnalyzerService triangleAnalyzerService;

    @Before
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

    @Test
    public void testValidation(){
        assertTrue(triangleAnalyzerService.validate(4,5,6));
    }
}
