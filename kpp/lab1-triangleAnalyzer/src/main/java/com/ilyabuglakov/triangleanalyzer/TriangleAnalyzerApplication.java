package com.ilyabuglakov.triangleanalyzer;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.context.annotation.ComponentScan;

@ComponentScan
@EnableAutoConfiguration
public class TriangleAnalyzerApplication {

	public static void main(String[] args) {
		SpringApplication.run(TriangleAnalyzerApplication.class, args);
	}

}
