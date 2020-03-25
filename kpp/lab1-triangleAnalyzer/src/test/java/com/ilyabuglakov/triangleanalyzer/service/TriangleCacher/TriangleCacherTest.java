package com.ilyabuglakov.triangleanalyzer.service.TriangleCacher;

import com.ilyabuglakov.triangleanalyzer.model.TriangleAnalyzer.TriangleAnalyzer;
import org.testng.Assert;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;

import static org.testng.Assert.*;

public class TriangleCacherTest {

    private static TriangleCacher<TriangleAnalyzer> cacher;
    private int pr1, pr2, pr3;
    private String param1, param2, param3;

    @BeforeMethod
    void init(){
        cacher = new TriangleCacher<>();
        pr1 = 1;
        pr2 = 2;
        pr3 = 3;
        param1 = "1";
        param2 = "2";
        param3 = "3";
    }

    @Test
    public void testGet() {
        TriangleAnalyzer ta = new TriangleAnalyzer(true, true, true);
        cacher.put("1-2-3", ta);
        Assert.assertEquals(cacher.get("1-2-3"), ta);
    }

    @Test
    public void testPut() {
        TriangleAnalyzer ta = new TriangleAnalyzer(true, true, true);
        Assert.assertEquals(cacher.put("1-2-3", ta), ta);
    }

    @Test
    public void testContainsByKey() {
        TriangleAnalyzer ta = new TriangleAnalyzer(true, true, true);
        cacher.put("1-2-3", ta);
        Assert.assertTrue(cacher.contains("1-2-3"));
    }

    @Test
    public void TestContainsByObject() {
        TriangleAnalyzer ta = new TriangleAnalyzer(true, true, true);
        cacher.put("1-2-3", ta);
        Assert.assertTrue(cacher.contains(ta));
    }

    @Test
    public void testFormKey() {
        Assert.assertEquals(cacher.formKey(pr1, pr2, pr3), cacher.formKey(param1, param2, param3));
    }

    @Test
    public void testKeyFormat() {
        String key = cacher.formKey(pr1, pr2, pr3);
        Assert.assertEquals(key, "1-2-3");
        key = cacher.formKey(param1,param2,param3);
        Assert.assertEquals(key, "1-2-3");
    }

}