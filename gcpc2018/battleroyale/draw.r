library("plotrix")
args = commandArgs(trailingOnly=TRUE)
if(length(args)<1) {
	stop("usage: draw.r testcase", call.=FALSE)
}
for(arg in args) {
cat("Input: ", arg, "\n")
df <- read.delim(arg, sep=" ", header=FALSE)
outFile <- paste0(arg, ".png")
png(outFile)
plot(-2000:2000, -2000:2000, type="n")
points(df[1, "V1"], df[1, "V2"], pch=3, col = "green")
points(df[2, "V1"], df[2, "V2"], pch=3, col = "black")
draw.circle(df[3, "V1"], df[3, "V2"], df[3, "V3"], nv=100, border="blue", col=NA, lty=1, lwd=1)
draw.circle(df[4, "V1"], df[4, "V2"], df[4, "V3"], nv=100, border="red", col=NA, lty=1, lwd=1)
dev.off()
}
