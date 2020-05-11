package com.ilyabuglakov.triangleanalyzer.service;

import com.ilyabuglakov.triangleanalyzer.application.exceptions.IllegalArgumentException;
import com.ilyabuglakov.triangleanalyzer.controller.TriangleAnalyzerController;
import com.ilyabuglakov.triangleanalyzer.model.Triangle;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class Validator{

    static final public Logger logger = LogManager.getLogger(TriangleAnalyzerController.class.getName());

    static public boolean softValidate(Triangle t){
        return softValidate(t.getSide1(), t.getSide2(), t.getSide3());
    }

    static public boolean softValidate(int sd1, int sd2, int sd3){
        if (!validateHelper(sd1, sd2, sd3)) {
            logger.error("Provided sides can't form a triangle:" +
                            " side1={}, side2={}, side3={}", sd1, sd2, sd3);
            return false;
        }
        return true;
    }

    static public boolean validate(Triangle t)
            throws IllegalArgumentException{
        return validate(t.getSide1(), t.getSide2(), t.getSide3());
    }

    static public boolean validate(int sd1, int sd2, int sd3)
    throws IllegalArgumentException{
        if (!validateHelper(sd1, sd2, sd3)) {
            throw new IllegalArgumentException(
                    String.format("Provided sides can't form a triangle:" +
                            " side1=%d, side2=%d, side3=%d", sd1, sd2, sd3));
        }
        else return true;
    }

    private static boolean validateHelper(int side1, int side2, int side3) {
        return validationCondition(side1, side2, side3) &&
                validationCondition(side1, side3, side2) &&
                validationCondition(side2,side3, side1) &&
                (side1>0&&side2>0&&side3>0);
    }

    private static boolean validationCondition(int side1, int side2, int side3) {
        return side1 + side2 > side3;
    }
}
