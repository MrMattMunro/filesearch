package com.searchlocal.util;

import org.apache.lucene.document.Document;

import com.searchlocal.bean.BaseFileBean;
import com.searchlocal.bean.ChmFileBean;
import com.searchlocal.bean.ExcelFileBean;
import com.searchlocal.bean.HtmlFileBean;
import com.searchlocal.bean.PdfFileBean;
import com.searchlocal.bean.PptFileBean;
import com.searchlocal.bean.TxtFileBean;
import com.searchlocal.bean.WordFileBean;
import com.searchlocal.constants.Constant;

public class BeanUtil {

	public static BaseFileBean getBean(Document element,String content) {

		String id = element.get("id");
		String filename = element.get("filename");
		String absolutepath = element.get("path");

		// �༭���������
		content = StringUtil.makeconent(content);
		String lastmodify = element.get("lastmodify");
		StringBuffer buf = new StringBuffer();

		buf.append(lastmodify.substring(0, 4));
		buf.append("-");
		buf.append(lastmodify.substring(4, 6));
		buf.append("-");
		buf.append(lastmodify.substring(6, 8));
		buf.append("/");
		buf.append(lastmodify.substring(8, 10));
		buf.append(":");
		buf.append(lastmodify.substring(10, lastmodify.length()));

		lastmodify = buf.toString();

		String suffixname = StringUtil.suffixName(filename);
		if (suffixname.equals(Constant.FileClassify.DOC) || suffixname.equals(Constant.FileClassify.DOC2007)  ) {
			WordFileBean filebean = new WordFileBean();
			filebean.setId(id);
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			filebean.setContent(content);

			String paragraphNo = element.get("paragraphNo");
			filebean.setParagraphNo(Integer.parseInt(paragraphNo));
			return filebean;
		}
		if (suffixname.equals(Constant.FileClassify.XLS) || suffixname.equals(Constant.FileClassify.XLS2007) ) {
			ExcelFileBean filebean = new ExcelFileBean();
			filebean.setId(id);
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			filebean.setContent(content);

			String sheetname = element.get("sheetname");
			filebean.setSheetname(sheetname);
			String rownb = element.get("rownb");
			filebean.setRownb(Integer.parseInt(rownb));
			return filebean;
		}
		if (suffixname.equals(Constant.FileClassify.PDF)) {
			PdfFileBean filebean = new PdfFileBean();
			filebean.setId(id);
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			filebean.setContent(content);

			String page = element.get("page");
			filebean.setPage(Integer.parseInt(page));
			return filebean;
		}
		if (suffixname.equals(Constant.FileClassify.PPT) || suffixname.equals(Constant.FileClassify.PPT2007)) {
			PptFileBean filebean = new PptFileBean();
			filebean.setId(id);
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			filebean.setContent(content);

			String page = element.get("page");
			filebean.setPage(Integer.parseInt(page));
			return filebean;
		}
		if (suffixname.equals(Constant.FileClassify.CHM)) {
			ChmFileBean filebean = new ChmFileBean();
			filebean.setId(id);
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			filebean.setContent(content);

			String catalogname = element.get("catalogname");
			filebean.setCatalogname(catalogname);
			return filebean;
		}
		if ((Constant.FileClassify.isHtmlcontain(suffixname))) {
			HtmlFileBean filebean = new HtmlFileBean();
			filebean.setId(id);
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			filebean.setContent(content);
			return filebean;
		}
		if (Constant.SrcClassify.iscontain(suffixname)) {
			TxtFileBean filebean = new TxtFileBean();
			filebean.setId(id);
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			filebean.setContent(content);

			String rownb = element.get("rownb");
			filebean.setRownb(Integer.parseInt(rownb));
			return filebean;
		}
		return null;
	}
}
