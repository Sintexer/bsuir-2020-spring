package com.ilyabuglakov.triangleanalyzer.service.analyzer;

import com.ilyabuglakov.triangleanalyzer.controller.TriangleAnalyzerController;
import com.ilyabuglakov.triangleanalyzer.model.AnalyzerResponseDto;
import com.ilyabuglakov.triangleanalyzer.model.Triangle;
import com.ilyabuglakov.triangleanalyzer.model.TriangleAttributes;
import com.ilyabuglakov.triangleanalyzer.service.RequestCounter;
import com.ilyabuglakov.triangleanalyzer.service.TriangleCacher;
import com.ilyabuglakov.triangleanalyzer.service.Validator;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;

@Service
public class TriangleAnalyzerService {

    static final public Logger logger = LogManager.getLogger(TriangleAnalyzerController.class.getName());

    @Autowired
    TriangleCacher<TriangleAttributes> cacher;
    @Autowired
    RequestCounter counter;

    public long getCounterValue(){
        return counter.getValue();
    }

    public TriangleAttributes formResponse(int sd1, int sd2, int sd3){
        counter.increment();
        Validator.validate(sd1, sd2, sd3);
        logger.info("Normal work. Provided sides: side1={}, side2={}, side3={}", sd1, sd2, sd3);
        return useCache(sd1, sd2, sd3);
    }

    public AnalyzerResponseDto formResponse(List<Triangle> triangles){
        counter.increment();
        final long total = triangles.size(),
                unique = triangles.stream().distinct().count();
        List<Triangle> validList = triangles.stream().distinct().filter(Validator::softValidate).collect(Collectors.toList());
        return new AnalyzerResponseDto(
                total, unique, unique - (long) validList.size(),
                validList.stream().filter(Validator::softValidate).map(t ->{
                    return formResponse(t.getSide1(), t.getSide2(), t.getSide3());
                }).collect(Collectors.toList()));
    }

    private TriangleAttributes useCache(int sd1, int sd2, int sd3){
        return cacher.contains(sd1,sd2,sd3) ?
                cacher.get(sd1,sd2,sd3):
                cacher.put(sd1, sd2, sd3, getAnalysis(sd1, sd2, sd3));
    }

    public TriangleAttributes getAnalysis(int sd1, int sd2, int sd3){
        return new TriangleAttributes(
                new Triangle(sd1, sd2, sd3),
                isEquilateral(sd1, sd2, sd3),
                isIsosceles(sd1, sd2, sd3),
                isRectangular(sd1, sd2, sd3));
    }

    public boolean isEquilateral(int side1, int side2, int side3) {
        return side1 == side2 && side2 == side3;
    }

    public boolean isEquilateral(Triangle t){
        return isEquilateral(t.getSide1(), t.getSide2(), t.getSide3());
    }

    public boolean isIsosceles(int side1, int side2, int side3) {
        return side1 == side2 || side2 == side3 || side1 == side3;
    }

    public boolean isIsosceles(Triangle t){
        return isIsosceles(t.getSide1(), t.getSide2(), t.getSide3());
    }

    public boolean isRectangular(int side1, int side2, int side3) {
        return rectangularCondition(side1, side2, side3) ||
                rectangularCondition(side2, side3, side1) ||
                rectangularCondition(side1, side3, side2);
    }

    public boolean isRectangular(Triangle t){
        return isIsosceles(t.getSide1(), t.getSide2(), t.getSide3());
    }

    private boolean rectangularCondition(int side1, int side2, int side3) {
        return Math.pow(side1, 2) + Math.pow(side2, 2) == Math.pow(side3, 2);
    }

}
