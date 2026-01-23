package com.example.appandroid


import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    private lateinit var drawingView: DrawingView
    private lateinit var resultText: TextView
    private lateinit var classifyBtn: Button
    private lateinit var clearBtn: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        drawingView = findViewById(R.id.drawingView)
        resultText = findViewById(R.id.resultText)
        classifyBtn = findViewById(R.id.classifyBtn)
        clearBtn = findViewById(R.id.clearBtn)

        classifyBtn.setOnClickListener {
            val bitmap = drawingView.getBitmap()
            val result = NativeLib.classify(bitmap)

            resultText.text = result
        }

        clearBtn.setOnClickListener {
            resultText.text = "Resultado"
            drawingView.clear()
        }
    }
}
