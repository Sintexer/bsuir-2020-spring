package com.ilyabuglakov.triangleanalyzer.service;


import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.junit4.SpringRunner;

import static org.junit.Assert.*;

@RunWith(SpringRunner.class)
public class DefaultTriangleAnalyzerServiceTest {

    private DefaultTriangleAnalyzerService defaultTriangleAnalyzerService;

    @Before
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
