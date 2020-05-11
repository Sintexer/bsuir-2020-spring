package com.ilyabuglakov.triangleanalyzer.model;

import java.util.LinkedList;
import java.util.List;

public class AnalyzerRequestDto {
    private List<Triangle> triangles;

    public List<Triangle> getTrianglesList() {
        return triangles;
    }

    public void setTrianglesList(List<Triangle> trianglesList) {
        this.triangles = trianglesList;
    }
}
