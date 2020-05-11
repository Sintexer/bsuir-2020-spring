package com.ilyabuglakov.triangleanalyzer.service;

import com.ilyabuglakov.triangleanalyzer.model.Triangle;
import com.ilyabuglakov.triangleanalyzer.model.TriangleAttributes;
import org.testng.Assert;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;

public class TriangleCacherTest {

    private static TriangleCacher<TriangleAttributes> cacher;
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
        TriangleAttributes ta = new TriangleAttributes(new Triangle(1,2,3),true, true, true);
        cacher.put("1-2-3", ta);
        Assert.assertEquals(cacher.get("1-2-3"), ta);
    }

    @Test
    public void testPut() {
        TriangleAttributes ta = new TriangleAttributes(new Triangle(1,2,3), true, true, true);
        Assert.assertEquals(cacher.put("1-2-3", ta), ta);
    }

    @Test
    public void testContainsByKey() {
        TriangleAttributes ta = new TriangleAttributes(new Triangle(1,2,3), true, true, true);
        cacher.put("1-2-3", ta);
        Assert.assertTrue(cacher.contains("1-2-3"));
    }

    @Test
    public void TestContainsByObject() {
        TriangleAttributes ta = new TriangleAttributes(new Triangle(1,2,3),true, true, true);
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