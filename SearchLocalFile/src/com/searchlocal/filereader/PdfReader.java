package com.searchlocal.filereader;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.pdfbox.cos.COSDocument;
import org.apache.pdfbox.pdfparser.PDFParser;
import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.util.PDFTextStripper;

import com.searchlocal.bean.PdfFileBean;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;

public class PdfReader {

	private static CLogger logger = new CLogger(PdfReader.class);

	public PdfReader() {
		super();
	}

	public List<PdfFileBean> getPdfFile(PdfFileBean pdfBean) throws LogicException {

		List<PdfFileBean> pdfEntityList = new ArrayList<PdfFileBean>();
		String result = null;
		FileInputStream is = null;
		COSDocument document = null;
		String pdfFilePath = pdfBean.getPath();
		try {
			is = new FileInputStream(pdfFilePath);
			PDFParser parser = new PDFParser(is);
			parser.parse();

			document = parser.getDocument();
			PDFTextStripper stripper = new PDFTextStripper();
			PDDocument pddoc = new PDDocument(document);

			PdfFileBean entity;
			if (document.isEncrypted()) {
				// 加密的情况只能得到整个文档,以后可以分解
				result = stripper.getText(pddoc);
				entity = new PdfFileBean();
				entity.setFilename(pdfBean.getFilename());
				entity.setLastmodify(pdfBean.getLastmodify());
				entity.setPath(pdfFilePath);
				entity.setContent(result);
				entity.setPage(0);
				pdfEntityList.add(entity);
			} else {
				int pageCount = 0;
				synchronized (this) {
					if (pddoc != null) {
						pageCount = pddoc.getNumberOfPages();
					}
				}
				for (int i = 1; i < pageCount; i++) {
					// 设置起始页
					stripper.setStartPage(i);
					// 设置结束页
					stripper.setEndPage(i);
					result = stripper.getText(pddoc);
					entity = new PdfFileBean();
					entity.setFilename(pdfBean.getFilename());
					entity.setLastmodify(pdfBean.getLastmodify());
					entity.setPath(pdfFilePath);
					entity.setContent(result);
					entity.setPage(i);
					pdfEntityList.add(entity);
				}
			}
		} catch (FileNotFoundException e) {
			logger.error("LG_E001", pdfFilePath);
			throw new LogicException("LG_E001", e);
		} catch (IOException e) {
			logger.error("LG_E003", pdfFilePath);
			throw new LogicException("LG_E003", e);
		} finally {
			if (is != null) {
				try {
					is.close();
				} catch (IOException e) {
					logger.error("LG_E003", pdfFilePath);
					throw new LogicException("LG_E003", e);
				}
			}
			if (document != null) {
				try {
					document.close();
				} catch (IOException e) {
					logger.error("LG_E003", pdfFilePath);
					throw new LogicException("LG_E003", e);
				}
			}
		}
		return pdfEntityList;
	}
}
