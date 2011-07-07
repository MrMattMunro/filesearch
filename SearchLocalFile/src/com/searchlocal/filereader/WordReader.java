package com.searchlocal.filereader;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import org.apache.poi.POIXMLDocument;
import org.apache.poi.hwpf.extractor.WordExtractor;
import org.apache.poi.xwpf.usermodel.XWPFDocument;
import org.apache.poi.xwpf.usermodel.XWPFParagraph;

import com.searchlocal.bean.WordFileBean;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.StringUtils;

public class WordReader {

	private static CLogger logger = new CLogger(WordReader.class);

	public List<WordFileBean> getWordFile(WordFileBean file) throws LogicException {

		String filepath = file.getPath();
		InputStream inputStream = null;
		try {
			inputStream = new FileInputStream(filepath);
			if (StringUtils.is2007Doc(filepath)) {
				XWPFDocument docx = new XWPFDocument(POIXMLDocument.openPackage(filepath));
				int pages = docx.getProperties().getExtendedProperties().getUnderlyingProperties()
						.getPages();// 总页数

				XWPFParagraph[] praragraph = docx.getParagraphs();
				int totalRow = praragraph.length;
				System.out.println("praragraph size" + praragraph.length);

				int row = praragraph.length / pages;
				WordFileBean fileBean;
				List beanList = new ArrayList();
				for (int i = 0; i < pages; i++) {
					StringBuffer content = new StringBuffer();
					fileBean = new WordFileBean();
					fileBean.setFilename(file.getFilename());
					fileBean.setPath(filepath);
					for (int j = 0; j < row; j++) {
						int index = i * row + j;
						if (index <= totalRow - 1) {
							content.append(praragraph[index].getParagraphText());
						}
					}
					fileBean.setParagraphNo(i + 1);
					fileBean.setContent(content.toString());
					fileBean.setLastmodify(file.getLastmodify());
					beanList.add(fileBean);
				}
				return beanList;
			} else {
				WordExtractor extractor = new WordExtractor(inputStream);
				return getBeanList(extractor, file);
			}

		} catch (FileNotFoundException e) {
			logger.error("LG_E001", filepath);
			throw new LogicException("LG_E001", e);
		} catch (IOException e) {
			logger.error("LG_E003", filepath);
			throw new LogicException("LG_E003", e);
		} finally {
			try {
				if (inputStream != null) {
					inputStream.close();
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}

	private List getBeanList(WordExtractor extractor, WordFileBean file) {
		String[] strs = extractor.getParagraphText();
		List<WordFileBean> beanList = new ArrayList<WordFileBean>();
		WordFileBean filebean;

		for (int i = 0; i < strs.length; i++) {
			String content = WordExtractor.stripFields(strs[i]);
			filebean = new WordFileBean();
			filebean.setFilename(file.getFilename());
			filebean.setPath(file.getPath());
			filebean.setLastmodify(file.getLastmodify());
			filebean.setContent(content);
			filebean.setParagraphNo(i + 1);
			beanList.add(filebean);
		}
		return beanList;
	}

	public static void main(String[] args) {
		try {
			WordReader reader = new WordReader();
			String excelFile = "E:\\test2007doc\\Senior Software Engineer.docx";
			// reader.getWordFile(excelFile);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
