---
title: Cheetsheet
layout: article
sidebar:
  nav: docs-en
---

# 1. Code block(liquid tag)
```markdown
{% highlight python %}
# Code here
{% endhighlight %}
```

---

# 2. LaTex
## 1) Bold
{% highlight LaTeX %}
\bf{}: 사용 이후에도 적용이 지속된다
\textbf{}: Text
\mathbf{}: Vector
\mathbb{}: Special set (Real set)
\mathcal{}: Laplace, Fourier transform의 그것
{% endhighlight %}

## 2) 복합 tag
- Color, bold, underline을 동시에 사용할 때 순서를 맞춰주어야 한다.

{% highlight LaTeX %}
\bf{\underline{\color{red}}}
{% endhighlight %}

## 3) Matrix
$$
\begin{aligned}
A =
\begin{pmatrix}
\\
\mathbf{a}_1 & \cdots & \mathbf{a}_n\\
\\
\end{pmatrix} =
\begin{pmatrix}
\\
\mathbf{b}_1 & \cdots & \mathbf{b}_r\\
\\
\end{pmatrix}
\begin{pmatrix}
c_{11} & \cdots & c_{1n}\\
\vdots & \ddots & \vdots\\
c_{r1} & \cdots & c_{rn}\\
\end{pmatrix}
= BC
\end{aligned}
$$

{% highlight LaTeX %}
$$
\begin{aligned}
A =
\begin{pmatrix}
\\
\mathbf{a}_1 & \cdots & \mathbf{a}_n\\
\\
\end{pmatrix} =
\begin{pmatrix}
\\
\mathbf{b}_1 & \cdots & \mathbf{b}_r\\
\\
\end{pmatrix}
\begin{pmatrix}
c_{11} & \cdots & c_{1n}\\
\vdots & \ddots & \vdots\\
c_{r1} & \cdots & c_{rn}\\
\end{pmatrix}
= BC
\end{aligned}
$$
{% endhighlight %}

## 4) Aligned equation
$$
\begin{equation}
\begin{aligned}
    p(x_k | Y_k) &= p(x_k | Y_{k-1}, y_k) \\
    &∝ p(y_k | Y_{k-1}, x_k) p(x_k | Y_{k-1}) \\
    &= p(y_k | x_k) p(x_k | Y_{k-1})
\end{aligned}
\end{equation}
$$

{% highlight LaTeX %}
$$
\begin{equation}
\begin{aligned}
    p(x_k | Y_k) &= p(x_k | y_k, Y_{k-1}) \\
    &∝ p(y_k | Y_{k-1}, x_k) p(x_k | Y_{k-1}) \\
    &= p(y_k | x_k) p(x_k | Y_{k-1})u
\end{aligned}
\end{equation}
$$
{% endhighlight %}


## Etc
{% highlight LaTeX %}
$ \stackrel{i.i.d.}{\sim} \\
\overset{above}{main} $
$\Vert W \Vert^2$
{% endhighlight %}

{% highlight LaTeX %}
\stackrel{i.i.d.}{\sim}
\overset{above}{main}
\Vert W \Vert^2<br>
{% endhighlight %}

---

# 3. TeXt
## 1) Alert
- Class: success, info, warning, error

**Title** \
Description
{:.success}

{% highlight markdown %}
**Title** \
Description
{:.success}
{% endhighlight %}

## 2) Tag
- Class: success, info, warning, error

`content`{:.success}

{% highlight markdown %}
`content`{:.success}
{% endhighlight %}

---

# 4. Image
<img src="https://raw.githubusercontent.com/kitian616/jekyll-TeXt-theme/master/docs/assets/images/image.jpg">

{% highlight markdown %}
<img src="https://raw.githubusercontent.com/kitian616/jekyll-TeXt-theme/master/docs/assets/images/image.jpg">
{% endhighlight %}

<img
  src="https://raw.githubusercontent.com/kitian616/jekyll-TeXt-theme/master/docs/assets/images/image.jpg"
  width="20%"
  height="20%">

{% highlight markdown %}
<img
  src="https://raw.githubusercontent.com/kitian616/jekyll-TeXt-theme/master/docs/assets/images/image.jpg"
  width="20%"
  height="20%">
{% endhighlight %}

![Image](https://raw.githubusercontent.com/kitian616/jekyll-TeXt-theme/master/docs/assets/images/image.jpg){:width="20" height="20"}{:.border}

{% highlight markdown %}
![Image](https://raw.githubusercontent.com/kitian616/jekyll-TeXt-theme/master/docs/assets/images/image.jpg){:width="20" height="20"}{:.border}
{% endhighlight %}

![picture 1](images/1debeb5e9da7c61b8c9a22844135247323ad609fb63cc371cffd485925c42836.jpg)  

{% highlight markdown %}
![picture 1](images/1debeb5e9da7c61b8c9a22844135247323ad609fb63cc371cffd485925c42836.jpg)  
{% endhighlight %}

---

# 5. YouTube
{% include extensions/youtube.html id = 'xYyL47hCTKA' %}

{% highlight markdown %}
{% include extensions/youtube.html id = 'xYyL47hCTKA' %}
{% endhighlight %}

---

# 6. 요약글
<details>
  <summary>요약글</summary>
  <div markdown="1">

    내용

  </div>
</details>

{% highlight markdown %}
<details>
  <summary>요약글</summary>
  <div markdown="1">

    내용

  </div>
</details>
{% endhighlight %}
