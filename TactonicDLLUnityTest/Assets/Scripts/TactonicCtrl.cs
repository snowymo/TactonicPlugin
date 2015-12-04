using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System.Collections.Generic;

public class TactonicCtrl : MonoBehaviour {

	struct TactonicObj{
		public List<int> lastFrame;
		public List<int> curFrame;
	};

	private int[] eachFrame;
	private float[] eachFrameImg;
	private TactonicObj m_tactObj;

	private int[] nCount;
	private int[] nTotal;
	
	// for cpp plugin
	[DllImport("TactonicDLL")]
	static extern bool getPressUp(int index);

	//[DllImport("SimpleDLL")]
	[DllImport("TactonicDLL")]
	static extern bool getPressDown(int index);

	[DllImport("SimpleDLL")]
	static extern int getInt();

	[DllImport("TactonicDLL")]
	static extern bool getFrame (int[] frame, int[] nCount, int[] nTotal);

	// Use this for initialization
	void Start () {
		// test for only one panel
		eachFrame = new int[48 * 80];
		eachFrameImg = new float[48 * 80];
		m_tactObj.curFrame = new List<int> ();
		m_tactObj.lastFrame = new List<int> (48 * 80);
		for(int i = 0; i < 48 * 80; i++){
			m_tactObj.curFrame.Add(0);
			m_tactObj.lastFrame.Add(0);
		}
		nCount = new int[1];
		nTotal = new int[1];
	}

	// Update is called once per frame
	void Update () {
		//bool b = getPressDown (0);
		//Debug.Log (b);
		nCount [0] = 0;
		nTotal [0] = 0;
		bool r = getFrame (eachFrame, nCount, nTotal);
		//Debug.Log (r);
		Debug.Log ("count:\t" + nCount[0]);
		//Debug.Log ("total:\t" + nTotal[0]);
		for (int i = 0; i < eachFrame.Length; i++) {
			m_tactObj.curFrame[i] = eachFrame[i];
			eachFrameImg[i] = (eachFrame[i] / 2000.0f);
			//if(eachFrame[i] != 0)
			//	Debug.Log(i / 80 + ":" + i % 80 + " is not empty");
		}
		//int a = getInt ();
		//Debug.Log (a);
		ExportAsImg ();
	}

	void ExportAsImg(){
		// export data in current frame to image;
		Texture2D tex = new Texture2D(80, 48, TextureFormat.RGB24, false);
		Material mainMat = GetComponent<Renderer> ().material;
		Texture mainTex = mainMat.mainTexture;
		Debug.Log (mainTex.height);
//		int w = mainTex.width;

		var colors = new Color[eachFrame.Length];
		for (int i = 0; i < eachFrame.Length; i++) {
			colors [i].r = eachFrameImg [i];
			colors [i].g = eachFrameImg [i];
			colors [i].b = eachFrameImg [i];
			//colors[i].a = 1.0f;
			//colors[i] = Color.green;
		}
		//tex.LoadImage (eachFrameImg);
		tex.SetPixels (colors);
		tex.Apply( true );
		GetComponent<Renderer>().material.mainTexture = tex;
	}
}
