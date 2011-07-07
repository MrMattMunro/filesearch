package com.searchlocal.filereader;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

import org.htmlparser.Node;
import org.htmlparser.NodeFilter;
import org.htmlparser.Parser;
import org.htmlparser.filters.NodeClassFilter;
import org.htmlparser.filters.OrFilter;
import org.htmlparser.nodes.TextNode;
import org.htmlparser.tags.TitleTag;
import org.htmlparser.util.NodeList;
import org.htmlparser.util.ParserException;

import com.searchlocal.bean.ChmFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.ConstantExeFileUtil;
import com.searchlocal.util.FileUtil;

/**
 * CHM读取类
 * 
 */
public class ChmReader {

	private static CLogger logger = new CLogger(ChmReader.class);

	private static List<ChmFileBean> returnList = new ArrayList<ChmFileBean>();

	public List<ChmFileBean> getChmFile(ChmFileBean bean) throws LogicException {

		String filepath = bean.getPath();
		ConstantExeFileUtil.readFile();
		String exepath = ConstantExeFileUtil.getOpenerbyId("chm");
		try {
			Runtime.getRuntime().exec(exepath + " -decompile" + " .\\chmtemp\\ " + filepath);
		} catch (IOException e) {
			e.printStackTrace();
		}

		ChmReader reader = new ChmReader();
		reader.getContent(new File(".\\chmtemp"), bean);

		// 删除临时下的文件
		FileUtil.delFolder(".\\chmtemp\\", false);

		return returnList;
	}

	public static void getContent(File file, ChmFileBean bean) throws LogicException {

		if (file.isDirectory()) {
			File[] files = file.listFiles();
			if (files != null) {
				for (int i = 0; i < files.length; i++) {
					getContent(files[i], bean);
				}
			}
		} else {
			String filename = file.getName();
			String filepath = file.getAbsolutePath();
			int length = filename.length() - 5;
			if (filename.indexOf(Constant.FileClassify.HTM, length) != -1
					|| filename.indexOf(Constant.FileClassify.HTML, length) != -1) {
				ChmFileBean filebean = new ChmFileBean();
				InputStream inputStream;
				StringBuffer sbStr = new StringBuffer();
				BufferedReader reader;
				try {
					inputStream = new FileInputStream(filepath);
					reader = new BufferedReader(new InputStreamReader(inputStream, "UTF-8"));
					String temp = "";
					while ((temp = reader.readLine()) != null) {
						sbStr.append(temp);
						sbStr.append("\r\n");
					}
					reader.close();
					String result = sbStr.toString();
					filebean.setFilename(bean.getFilename());
					filebean.setPath(bean.getPath());
					filebean.setLastmodify(bean.getLastmodify());
					filebean.setContent(readTextAndTitle(result));
					filebean.setCatalogname(filename);
					returnList.add(filebean);
				} catch (FileNotFoundException e) {
					logger.error("LG_E001", filepath);
					throw new LogicException("LG_E001", e);
				} catch (UnsupportedEncodingException e) {
					logger.error("LG_E002", filepath);
					throw new LogicException("LG_E002", e);
				} catch (IOException e) {
					logger.error("LG_E003", filepath);
					throw new LogicException("LG_E003", e);
				} catch (ParserException e) {
					logger.error("LG_E004", filepath);
					throw new LogicException("LG_E004", e);
				} catch (Exception e) {
					logger.error("", filepath);
					throw new LogicException("", e);
				}
			}
		}
	}

	// 读取文本内容和标题
	public static String readTextAndTitle(String result) throws Exception {
		Parser parser;
		NodeList nodelist;
		parser = Parser.createParser(result, "UTF-8");
		NodeFilter textFilter = new NodeClassFilter(TextNode.class);
		NodeFilter titleFilter = new NodeClassFilter(TitleTag.class);
		OrFilter lastFilter = new OrFilter();
		lastFilter.setPredicates(new NodeFilter[] { textFilter, titleFilter });
		nodelist = parser.parse(lastFilter);
		Node[] nodes = nodelist.toNodeArray();
		String line = "";
		StringBuffer bf = new StringBuffer();
		for (int i = 0; i < nodes.length; i++) {
			Node node = nodes[i];
			if (node instanceof TextNode) {
				TextNode textnode = (TextNode) node;
				line = textnode.getText();
			} else if (node instanceof TitleTag) {
				TitleTag titlenode = (TitleTag) node;
				line = titlenode.getTitle();
			}
			if (isTrimEmpty(line))
				continue;
			bf.append(line);
		}
		return bf.toString();
	}

	/**
	 * 去掉左右空格后字符串是否为空
	 */
	public static boolean isTrimEmpty(String astr) {
		if ((null == astr) || (astr.length() == 0)) {
			return true;
		}
		if (isBlank(astr.trim())) {
			return true;
		}
		return false;
	}

	/**
	 * 字符串是否为空:null或者长度为0.
	 */
	public static boolean isBlank(String astr) {
		if ((null == astr) || (astr.length() == 0)) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * @return Returns the returnList.
	 */
	public static List getReturnList() {
		return returnList;
	}

	/**
	 * @param returnList
	 *            The returnList to set.
	 */
	public static void setReturnList(List returnList) {
		ChmReader.returnList = returnList;
	}

}
