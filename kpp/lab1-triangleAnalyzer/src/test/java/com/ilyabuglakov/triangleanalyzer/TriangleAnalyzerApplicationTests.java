package com.ilyabuglakov.triangleanalyzer;

import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

@RunWith(SpringRunner.class)
public class TriangleAnalyzerApplicationTests {

	@Test
	public void testStartup() throws Exception {
		TriangleAnalyzerApplication.main(new String[]{});
	}

}
