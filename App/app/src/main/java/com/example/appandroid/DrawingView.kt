package com.example.appandroid


import android.content.Context
import android.graphics.*
import android.util.AttributeSet
import android.view.MotionEvent
import android.view.View

class DrawingView(context: Context, attrs: AttributeSet) : View(context, attrs) {

    private val paint = Paint().apply {
        color = Color.WHITE
        strokeWidth = 20f
        style = Paint.Style.STROKE
        isAntiAlias = true
    }

    private val path = Path()
    private lateinit var bitmap: Bitmap
    private lateinit var canvasBmp: Canvas

    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
        bitmap = Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888)
        canvasBmp = Canvas(bitmap)
        canvasBmp.drawColor(Color.BLACK)
    }

    override fun onDraw(canvas: Canvas) {
        canvas.drawBitmap(bitmap, 0f, 0f, null)
        canvas.drawPath(path, paint)
    }

    override fun onTouchEvent(event: MotionEvent): Boolean {
        val x = event.x
        val y = event.y

        when (event.action) {
            MotionEvent.ACTION_DOWN -> path.moveTo(x, y)
            MotionEvent.ACTION_MOVE -> path.lineTo(x, y)
        }

        canvasBmp.drawPath(path, paint)
        invalidate()
        return true
    }

    fun getBitmap(): Bitmap = bitmap

    fun clear() {
        path.reset()
        canvasBmp.drawColor(Color.BLACK)
        invalidate()
    }
}
