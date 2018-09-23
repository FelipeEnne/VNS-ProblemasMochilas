\ LP format - for model browsing. Use MPS format to capture full model detail.
Minimize
  5 l1 + 7 l2 + 11 l3 + 11 l4 + 4 l5 + 3 l6 + 3 l7 + 9 l8 + 3 l9 + 9 l10
Subject To
 c1: l1 + 3 l2 + 3 l3 + 3 l4 + 2 l5 + l6 + 2 l8 + l9 + 2 l10 = 1
 c2: l1 + 3 l3 + 2 l4 + l6 + l7 + 2 l10 = 1
 c3: l1 + 2 l4 + l7 + 3 l8 + l9 + 2 l10 = 1
 c4: l1 + l2 + l3 + l4 + l5 + l6 + l7 + l8 + l9 + l10 = 1
Bounds
End
