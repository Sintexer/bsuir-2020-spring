package com.ilyabuglakov.triangleanalyzer.controller;

import com.ilyabuglakov.triangleanalyzer.application.exceptions.InternalServerErrorException;
import com.ilyabuglakov.triangleanalyzer.config.TestSpringConfig;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.test.context.testng.AbstractTestNGSpringContextTests;
import org.testng.Assert;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;

@ActiveProfiles("test")
@SpringBootTest(classes = TestSpringConfig.class)
public class TriangleAnalyzerControllerTest extends AbstractTestNGSpringContextTests {

//    private TriangleAnalyzerController controller;
//
//    @BeforeMethod
//    private void initController() {
//        controller = new TriangleAnalyzerController();
//    }
//
//    @Test(expectedExceptions = InternalServerErrorException.class)
//    void testIllegalArgument() {
//        String side1 = "3", side2 = "4", side3 = "5";
//        controller.triangleAnalyzer(side1, side2, side3);
//        Assert.fail();
//    }

}
