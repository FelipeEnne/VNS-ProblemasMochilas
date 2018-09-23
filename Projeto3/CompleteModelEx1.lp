\ LP format - for model browsing. Use MPS format to capture full model detail.
Minimize
  2 x11 + x21 + x31 + x12 + 2 x22 + x32 + x13 + x23 + 2 x33 + y1 + y2 + y3
Subject To
 c1: x11 - y1 <= 0
 c2: x12 - y1 <= 0
 c3: x13 - y1 <= 0
 c4: x21 - y2 <= 0
 c5: x22 - y2 <= 0
 c6: x23 - y2 <= 0
 c7: x31 - y3 <= 0
 c8: x32 - y3 <= 0
 c9: x33 - y3 <= 0
 c10: x11 + x21 + x31 = 1
 c11: x12 + x22 + x32 = 1
 c12: x13 + x23 + x33 = 1
Bounds
 x11 <= 1
 x21 <= 1
 x31 <= 1
 x12 <= 1
 x22 <= 1
 x32 <= 1
 x13 <= 1
 x23 <= 1
 x33 <= 1
 y1 <= 1
 y2 <= 1
 y3 <= 1
End
