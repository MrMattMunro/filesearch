package com.searchlocal.menu.jp ;

import java.awt.Color;
import java.awt.Container;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.border.TitledBorder;
import javax.swing.filechooser.FileFilter;

import org.pushingpixels.substance.api.SubstanceLookAndFeel;
import org.pushingpixels.substance.api.skin.SubstanceBusinessBlackSteelLookAndFeel;

import com.searchlocal.constants.Constant;
import com.searchlocal.filereader.ExcelToDicReader;
import com.searchlocal.menu.CFrame;
import com.searchlocal.menu.CPanel;
import com.searchlocal.menu.MessageFrame;
import com.searchlocal.menu.SearchlocalApp;
import com.searchlocal.thread.createindex.ReCreateIndex;
import com.searchlocal.util.FileUtil;
import com.searchlocal.util.MenuMessageUtil;
import com.searchlocal.util.StringUtils;

public class JPAddDicFrame extends CFrame implements ActionListener {

	private static final long serialVersionUID = 1L;

	static JPAddDicFrame c;

	// search name
	static JTextField searchnamefield;

	private static MenuMessageUtil msg = new MenuMessageUtil();

	public static String title_adddic = msg.getMsgbyId(Constant.title_adddic);

	public static String file_chooser_selectdicpath = msg.getMsgbyId(Constant.file_chooser_selectdicpath);

	public static String label_dic_file = msg.getMsgbyId(Constant.label_dicfilename);

	public static String label_dic_note_r1 = msg.getMsgbyId(Constant.label_dic_note_r1);
	
	public static String label_dic_note_r2 = msg.getMsgbyId(Constant.label_dic_note_r2);
	
	public static String label_dic_note_r3 = msg.getMsgbyId(Constant.label_dic_note_r3);
	
	public static String checkbox_iscoverdic = msg.getMsgbyId(Constant.checkbox_iscoverdic);
	
	public static String infonodic = msg.getMsgbyId(Constant.info_nodic);
	
	// select dir
	JFileChooser filechooser = new JFileChooser();
	JTextField selectdir = null;
	JTextField selectindexdir = null;

	// selectindex dir
	JFileChooser dicfilechooser = new JFileChooser();
	JButton selectdicfilebotton = null;
	
	// selectindex dir
	JButton viewdicbotton = null;
	
	// checkbox
	JCheckBox coverdiccheckbox = null;

	public JPAddDicFrame() {

		Container container = getContentPane();
		container.setLayout(null);
		setTitle(msg.getMsgbyId(Constant.title_adddic));

		CPanel panel = new CPanel();
		panel.setLayout(null);
	    panel.setBounds(5, 5, 500, 294);
		TitledBorder border = new TitledBorder("");
		border.setBorder(BorderFactory.createEtchedBorder(Color.orange, Color.BLUE));
		panel.setBorder(border);
		
		panel.makeLabel(label_dic_note_r1, 35, 10, 400, 50);
		panel.makeLabel(label_dic_note_r2, 35, 30, 400, 50);
		panel.makeLabel(label_dic_note_r3, 35, 50, 400, 50);
		
		panel.makeLabel(label_dic_file, 32, 110, 110, 25);
		selectdir = panel.makeTextField(115, 110, 278, 20);
		selectdir.setEditable(false);

		JButton selectdirbotton = panel.makeButton(msg.getMsgbyId(Constant.button_select),400, 110, 60, 20,"");
		selectdirbotton.putClientProperty(SubstanceLookAndFeel.BUTTON_NO_MIN_SIZE_PROPERTY, Boolean.TRUE);

        selectdirbotton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				filechooser.setDialogTitle(file_chooser_selectdicpath);
				filechooser.addChoosableFileFilter(new DicFilter());
				filechooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
				int state = filechooser.showOpenDialog(null);
				File file = filechooser.getSelectedFile();
				if (file != null && state == JFileChooser.APPROVE_OPTION) {
					selectdir.setText(file.getAbsolutePath());
				}
			}
		});

        coverdiccheckbox = panel.makeCheckbox(checkbox_iscoverdic, 29, 160, 230, 20, "");
		// 查看字典按钮
		viewdicbotton = panel.makeButton(msg.getMsgbyId(Constant.button_viedic), 260, 160, 200, 20,"");
		viewdicbotton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				   String dicfilepath = Constant.dicpath + "custom.dic";
				   File file = new File(dicfilepath);
				   if(!file.exists()){
					    String errormsg = msg.getMsgbyId(Constant.errors_dicnotexisted);
					    MessageFrame.showmessage(errormsg);
					    return;
				   }
					JPShowDicFrame viewDic = new JPShowDicFrame();
					try {
						viewDic.showframe();
					} catch (UnsupportedLookAndFeelException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (ClassNotFoundException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (InstantiationException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (IllegalAccessException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
			}
		});
		
        // 确认
		JButton confirmbutton = panel.makeButton(msg.getMsgbyId(Constant.button_confirm), 160, 210, 80, 20, "");
		confirmbutton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				SearchlocalApp.startWork(Constant.ToolTipsClassify.TOOLTIPS_UPDATINGINDEX);
				String filepath = selectdir.getText();
				if (MessageFrame.checkISnotDicString(filepath)) {
					String suffixname = StringUtils.suffixName(filepath);
					String dicfilepath = Constant.dicpath + "custom.dic";
					// 选择覆盖原有的自定义词典
					if (coverdiccheckbox.isSelected()) {
						File dicfile = new File(dicfilepath);
						if (!dicfile.exists()) {
							MessageFrame.showmessage(infonodic);
						}
						createDic(suffixname, filepath, dicfilepath);
					} else {
						// 不覆盖原有的词典
						File dicfile = new File(dicfilepath);
						if (!dicfile.exists()) {
							MessageFrame.showmessage(infonodic);
						}
						appendDic(suffixname, filepath, dicfilepath);
					}
					
					//删除字典文件里空行
					FileUtil.deleteNullLine(dicfilepath);

					// 删除已经编译后的词典
					FileUtil.delFolder(Constant.diccompilepath, false);

					c.setVisible(false);
					//增加了词库需要所有都需要重新建索引
					if(ReCreateIndex.listen()){
						SearchlocalApp.completeWork();	
					}
			
					String completeemsg = msg.getMsgbyId(Constant.info_updatedindex);
					MessageFrame.showmessage(completeemsg);
				}
			}
		});
		
		// 取消按钮
		JButton cancelbutton = panel.makeButton(msg.getMsgbyId(Constant.button_cancel), 260, 210, 80, 20,"");
		cancelbutton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				c.setVisible(false);
			}
		});
	
		container.add(panel);
		this.setSize(520, 300);
		this.setLocationRelativeTo(null);
		this.setResizable(false);
	}

	public static void showframe() throws UnsupportedLookAndFeelException,
			ClassNotFoundException, InstantiationException{
		

		    JFrame.setDefaultLookAndFeelDecorated(true);
			SwingUtilities.invokeLater(new Runnable() {
				public void run() {
					try {
						UIManager.setLookAndFeel(new SubstanceBusinessBlackSteelLookAndFeel());
					} catch (UnsupportedLookAndFeelException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					c = new JPAddDicFrame();
					c.setIconImage(Toolkit.getDefaultToolkit().getImage(Constant.titleicopath));
					c.setVisible(true);
				}
			});
			
	}

	public void actionPerformed(ActionEvent e) {

	}
	
	public static void main(String[] args){
		try {
			
			JPAddDicFrame frame = new JPAddDicFrame();
			frame.showframe();
		} catch (UnsupportedLookAndFeelException e) {
			// TODO 自动生成 catch 部分
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO 自动生成 catch 部分
			e.printStackTrace();
		} catch (InstantiationException e) {
			// TODO 自动生成 catch 部分
			e.printStackTrace();
		} 
	}

	private void createDic(String suffixname, String filepath, String dicfilepath) {
		// 当是文本文件时
		if (suffixname.endsWith(Constant.FileClassify.TXT)) {
			File txtfile = new File(filepath);
			FileUtil.copyFile(txtfile, new File(dicfilepath));
		}
		// 当是xls文件时
		if (suffixname.endsWith(Constant.FileClassify.XLS) || suffixname.endsWith(Constant.FileClassify.XLS2007)) {
			File excelfile = new File(filepath);
			ExcelToDicReader.getExcelFile(excelfile, new File(dicfilepath));
		}
	}
	
	private void appendDic(String suffixname, String filepath, String dicfilepath) {
		String temp = "";
		// 当是文本文件时
		if (suffixname.endsWith(Constant.FileClassify.TXT)) {
			temp = FileUtil.readText(filepath);
		}
		// 当是xls文件时
		if (suffixname.endsWith(Constant.FileClassify.XLS) || suffixname.endsWith(Constant.FileClassify.XLS2007)) {
			temp = ExcelToDicReader.getExcelContent(new File(filepath));
		}
		FileUtil.appendText(dicfilepath, temp);
	}

	class DicFilter extends FileFilter {
		public boolean accept(File file) {
			String filename = file.getName().toLowerCase();
			return filename.endsWith(".xlsx") || filename.endsWith(".xls") ||filename.endsWith(".txt") || file.isDirectory();
		}

		public String getDescription() {
			return "";
		}
	}

}
