package com.ilyabuglakov.triangleanalyzer.service.converter;

import com.ilyabuglakov.triangleanalyzer.entity.TriangleEntity;
import com.ilyabuglakov.triangleanalyzer.model.Triangle;
import org.springframework.stereotype.Service;

@Service
public class TriangleConverter extends Converter<Triangle, TriangleEntity> {

    public TriangleConverter(){
        super(TriangleConverter::convertToEntity, TriangleConverter::convertToDto);
    }

    private static TriangleEntity convertToEntity(Triangle triangle){
        return new TriangleEntity(triangle.getSide1(), triangle.getSide2(), triangle.getSide3());
    }

    private static Triangle convertToDto(TriangleEntity triangle){
        return new Triangle(triangle.getSide1(), triangle.getSide2(), triangle.getSide3());
    }
}
