package com.ilyabuglakov.triangleanalyzer.model;

import java.util.List;

public class AnalyzerResponseDto {
    long totalRequestsCount;
    long uniqueRequestCount;
    long invalidRequestCount;
    List<TriangleAttributes> responseList;

    public long getTotalRequestsCount() {
        return totalRequestsCount;
    }

    public void setTotalRequestsCount(long totalRequestsCount) {
        this.totalRequestsCount = totalRequestsCount;
    }

    public long getUniqueRequestCount() {
        return uniqueRequestCount;
    }

    public void setUniqueRequestCount(long uniqueRequestCount) {
        this.uniqueRequestCount = uniqueRequestCount;
    }

    public long getInvalidRequestCount() {
        return invalidRequestCount;
    }

    public void setInvalidRequestCount(long invalidRequestCount) {
        this.invalidRequestCount = invalidRequestCount;
    }

    public List<TriangleAttributes> getResponseList() {
        return responseList;
    }

    public void setResponseList(List<TriangleAttributes> responseList) {
        this.responseList = responseList;
    }

    public AnalyzerResponseDto(long totalRequestCount, long uniqueRequestCount, long invalidRequestCount, List<TriangleAttributes> responseList) {
        this.totalRequestsCount = totalRequestCount;
        this.uniqueRequestCount= uniqueRequestCount;
        this.invalidRequestCount = invalidRequestCount;
        this.responseList = responseList;
    }

    public AnalyzerResponseDto(){}
}