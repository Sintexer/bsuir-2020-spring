package com.ilyabuglakov.triangleanalyzer.model;

public class Triangle {
    private int side1;
    private int side2;
    private int side3;

    public Triangle(int sd1, int sd2, int sd3){ side1 = sd1; side2 = sd2; side3 = sd3; }

    public int getSide1() {
        return side1;
    }

    public void setSide1(int side1) {
        this.side1 = side1;
    }

    public int getSide2() {
        return side2;
    }

    public void setSide2(int side2) {
        this.side2 = side2;
    }

    public int getSide3() {
        return side3;
    }

    public void setSide3(int side3) {
        this.side3 = side3;
    }
}
