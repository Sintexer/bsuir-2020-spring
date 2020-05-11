package com.ilyabuglakov.triangleanalyzer.model;

import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;

import static org.testng.Assert.assertFalse;
import static org.testng.Assert.assertTrue;


public class TriangleAnalyzerTest {

    private TriangleAttributes triangleAttributes;

    @BeforeMethod
    public void setup(){
        triangleAttributes = new TriangleAttributes(new Triangle(4,4,4),true, true, false);
    }

    @Test
    public void testSetEquilaterial(){
        triangleAttributes.setEquilateral(false);
        assertFalse(triangleAttributes.isEquilateral());
    }

    @Test
    public void testSetIsosceles(){
        triangleAttributes.setIsosceles(false);
        assertFalse(triangleAttributes.isRectangular());
    }

    @Test
    public void testSetRectangular(){
        triangleAttributes.setRectangular(true);
        assertTrue(triangleAttributes.isRectangular());
    }

}
