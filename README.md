# Random-Text-Generator

Генератор описания хода гонки по заранее известному протоколу.

## Beautifier

Теги, используемые функцией `beautifySentence(...)` для осуществления верной, с точки зрения русского языка, подстановки 
случайных слов и фраз:

Тег | Значение
---|---
`PRT` | участник
`ADJ_GOOD_ng` | хорошее прил. в ср.р.
`ADJ_GOOD_mg` | хорошее прил в м.р.
`ADJ_BAD_ng` | плохое прил. в ср.р.
`ADJ_BAD_mg` | плохое прил в м.р.
`ADV_GOOD` | хорошее нар.
`ADV_BAD` | плохое нар.
`ADV_TOUGH` | "закономерно" нар.
`ADV_ACC` | неожиданно нар.
`VERB_WILL` | гл. волеизъявления
`VERB_WIN` | гл. побеждать
`VERB_ERR` | гл. ошибки
`VERB_SHOW` | гл. показать
`VERB_TAKEOFF` | гл. начала
`EXC_GOOD` | хорошее восклицание
`EXC_BAD` | плохое восклицание
`MOVE` | движение, маневр
`OVER` | обгон
`TURN` | поворот
`FIGHT` | противостояние
`1stPRIZE` | 1 место турнира