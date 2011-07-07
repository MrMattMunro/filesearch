package com.searchlocal.util;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import com.searchlocal.constants.Constant;
import com.searchlocal.param.CreateNewParam;

public class XMLConfig {

	private static CLogger logger = new CLogger(XMLConfig.class);

	private static Document doc;

	/*
	 * use a path to create a XMLConfigUtil
	 */
	public XMLConfig() {

	}

	public void readXML(String configPath) {
		try {

			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder builder = dbFactory.newDocumentBuilder();
			this.doc = builder.parse(new File(configPath));
		} catch (ParserConfigurationException e) {
			e.printStackTrace();
		} catch (SAXException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public List getEntityList() {
		logger.debug(Constant.path+ "com\\searchlocal\\properties\\searchers.xml");
		
		NodeList nodelist = null;
		if(null == this.doc){
			this.readXML(Constant.path + "com\\searchlocal\\properties\\searchers.xml");
			System.out.println("config path:::" +Constant.path + "com\\searchlocal\\properties\\searchers.xml");
		}
		nodelist = this.doc.getElementsByTagName("searcher");

		List entityList = new ArrayList();
		for (int i = 0; i < nodelist.getLength(); i++) {
			Node node = nodelist.item(i);
			NodeList cnodeList = node.getChildNodes();
			CreateNewParam newparam = new CreateNewParam();
			for (int j = 0; j < cnodeList.getLength(); j++) {
				Node cnode = cnodeList.item(j);
				if (cnode.getNodeName().indexOf("indexpath") != -1) {
					newparam.setIdexpath(cnode.getTextContent().trim());
				}
				if (cnode.getNodeName().indexOf("searchpath") != -1) {
					newparam.setPath(cnode.getTextContent().trim());
				}
				if (cnode.getNodeName().indexOf("searchname") != -1) {
					newparam.setSearchname(cnode.getTextContent().trim());
				}
				if (cnode.getNodeName().indexOf("types") != -1) {
					List typeList = Arrays.asList(cnode.getTextContent().split(
							","));
					newparam.setSelectfiletype(typeList);
				}
			}
			entityList.add(newparam);
		}
		return entityList;
	}

	public static List getList() {
		XMLConfig xmlconfig = new XMLConfig();
		List entityList = xmlconfig.getEntityList();
		return entityList;
	}

}
