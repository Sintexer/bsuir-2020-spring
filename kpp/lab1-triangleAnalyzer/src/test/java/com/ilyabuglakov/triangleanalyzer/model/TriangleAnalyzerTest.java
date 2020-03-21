package com.ilyabuglakov.triangleanalyzer.model;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.junit4.SpringRunner;

import static org.junit.Assert.*;

@RunWith(SpringRunner.class)
public class TriangleAnalyzerTest {

    private TriangleAnalyzer triangleAnalyzer;

    @Before
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
