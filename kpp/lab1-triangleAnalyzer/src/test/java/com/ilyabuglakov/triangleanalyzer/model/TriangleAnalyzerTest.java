package com.ilyabuglakov.triangleanalyzer.model;

import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;

import static org.testng.Assert.assertFalse;
import static org.testng.Assert.assertTrue;


public class TriangleAnalyzerTest {

    private TriangleAnalyzer triangleAnalyzer;

    @BeforeMethod
    public void setup(){
        triangleAnalyzer = new TriangleAnalyzer(true, true, false);
    }

    @Test
    public void testSetEquilaterial(){
        triangleAnalyzer.setEquilateral(false);
        assertFalse(triangleAnalyzer.isEquilateral());
    }

    @Test
    public void testSetIsosceles(){
        triangleAnalyzer.setIsosceles(false);
        assertFalse(triangleAnalyzer.isRectangular());
    }

    @Test
    public void testSetRectangular(){
        triangleAnalyzer.setRectangular(true);
        assertTrue(triangleAnalyzer.isRectangular());
    }

}
