package com.searchlocal.filereader;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.poi.hslf.HSLFSlideShow;
import org.apache.poi.hslf.model.Slide;
import org.apache.poi.hslf.model.TextRun;
import org.apache.poi.hslf.usermodel.SlideShow;
import org.apache.poi.openxml4j.exceptions.OpenXML4JException;
import org.apache.poi.xslf.XSLFSlideShow;
import org.apache.poi.xslf.extractor.XSLFPowerPointExtractor;
import org.apache.poi.xslf.usermodel.XMLSlideShow;
import org.apache.poi.xslf.usermodel.XSLFSlide;
import org.apache.xmlbeans.XmlException;
import org.openxmlformats.schemas.drawingml.x2006.main.CTRegularTextRun;
import org.openxmlformats.schemas.drawingml.x2006.main.CTTextBody;
import org.openxmlformats.schemas.drawingml.x2006.main.CTTextParagraph;
import org.openxmlformats.schemas.presentationml.x2006.main.CTGroupShape;
import org.openxmlformats.schemas.presentationml.x2006.main.CTShape;
import org.openxmlformats.schemas.presentationml.x2006.main.CTSlide;

import com.searchlocal.bean.PptFileBean;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.StringUtils;

public class PptReader {

	private static CLogger logger = new CLogger(PptReader.class);

	public PptReader() {
		super();
	}

	public List getPptFile(String pptFilePath) throws LogicException {
		List<PptFileBean> pptEntityList = new ArrayList<PptFileBean>();
		FileInputStream is = null;
		try {
			is = new FileInputStream(pptFilePath);
			SlideShow ss;
			Slide[] slides = null;
			if (StringUtils.is2007Doc(pptFilePath)) {
				//将源文件转换成xml格式
				XMLSlideShow xmlslideshow = null;
				try {
					xmlslideshow = new XMLSlideShow(new XSLFSlideShow(pptFilePath));
					//根据xml格式的文件得到一个ppt对象
					XSLFPowerPointExtractor ppt = new XSLFPowerPointExtractor(xmlslideshow);
					return  getBeanList(xmlslideshow.getSlides());
				} catch (XmlException e) {
					// TODO 注意消除资源(关闭I/O等)
					e.printStackTrace();
				} catch (OpenXML4JException e) {
					// TODO 注意消除资源(关闭I/O等)
					e.printStackTrace();
				}
			} else {
				ss = new SlideShow(new HSLFSlideShow(is));
				slides = ss.getSlides();
			}

			PptFileBean entity = null;
			StringBuffer content = null;
			for (int i = 0; i < slides.length; i++) {
				entity = new PptFileBean();
				content = new StringBuffer();
				content.append(slides[i].getTitle());
				TextRun[] t = slides[i].getTextRuns();
				for (int j = 0; j < t.length; j++) {
					content.append(t[j].getText());
				}

				entity = new PptFileBean();
				entity.setContent(content.toString());
				entity.setPage(i);
				pptEntityList.add(entity);
			}
		} catch (FileNotFoundException e) {
			logger.error("LG_E001", pptFilePath);
			throw new LogicException("LG_E001", e);
		} catch (IOException e) {
			logger.error("LG_E003", pptFilePath);
			throw new LogicException("LG_E003", e);
		} finally {
			try {
				if (is != null) {
					is.close();
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return pptEntityList;
	}

	public List getBeanList(XSLFSlide[] slides) {
		PptFileBean entity = null;
		StringBuffer content = null;
		List beanList = new ArrayList();
		for (int i = 0; i < slides.length; i++) {
			entity = new PptFileBean();
			content = new StringBuffer();
			org.apache.poi.xslf.usermodel.XSLFSlide xslfSlide = slides[i];
			CTSlide rawSlide = xslfSlide._getCTSlide();
			CTGroupShape gs = rawSlide.getCSld().getSpTree();
			CTShape[] shapes = gs.getSpArray();
			for (CTShape shape : shapes) {
				CTTextBody tb = shape.getTxBody();
				if (null == tb)
					continue;
				CTTextParagraph[] paras = tb.getPArray();
				for (CTTextParagraph textParagraph : paras) {
					CTRegularTextRun[] textRuns = textParagraph.getRArray();
					for (CTRegularTextRun textRun : textRuns) {
						content.append(textRun.getT());
					}
				}
			}
			entity.setContent(content.toString());
			entity.setPage(i);
			beanList.add(entity);
		}
		return beanList;
	}
}
