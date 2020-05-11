package com.ilyabuglakov.triangleanalyzer.service.TriangleAnalyzerService;

import com.ilyabuglakov.triangleanalyzer.model.Triangle;
import com.ilyabuglakov.triangleanalyzer.model.TriangleAttributes;
import org.springframework.stereotype.Service;

@Service
public class TriangleAnalyzerService implements ITriangleAnalyzerService {

    public TriangleAttributes formResponse(int side1, int side2, int side3){
        return new TriangleAttributes(
                new Triangle(side1, side2, side3),
                isEquilateral(side1, side2, side3),
                isIsosceles(side1, side2, side3),
                isRectangular(side1, side2, side3));
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
