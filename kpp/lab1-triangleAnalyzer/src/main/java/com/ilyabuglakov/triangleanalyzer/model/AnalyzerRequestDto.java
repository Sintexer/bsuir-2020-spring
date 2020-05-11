package com.ilyabuglakov.triangleanalyzer.model;

import java.util.ArrayList;
import java.util.List;

public class AnalyzerRequestDto {
    private List<Triangle> triangles;

    public List<Triangle> getTriangles() {
        return triangles;
    }

    public void setTrianglesList(List<Triangle> triangles) {
        this.triangles = triangles;
    }
}
