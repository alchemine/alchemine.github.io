---
title: Adjusting Width for Jekyll Blog
tags: Programming_Etc
---

<!--more-->

`_sass/common/_variables.scss` 에서 다음 부분을 변경한다.

```scss
...

$layout: (
  header-height:          5rem,
  header-height-sm:       3rem,
  content-max-width:      1500px,  // 950px -> 1500px
  sidebar-width:          300px,   // 250px -> 300px
  sidebar-header-height:  3rem,
  aside-width:            300px,   // 220px -> 300px
);

...
```
