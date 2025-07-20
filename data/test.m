logisticR2;
logisticR2.Properties;
props = logisticR2.Properties;
props.VariableTypes

tab = readtable("logistic-R0.050000.csv",TextType="string")
tab.Properties
tab.Iters(:,1) = zeros(size(tab.Iters,1),1)
