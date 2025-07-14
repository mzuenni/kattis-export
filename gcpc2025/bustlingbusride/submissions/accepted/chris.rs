use std::{
    fmt::Debug,
    io::{self, BufWriter, StdoutLock, Write},
    iter::FromIterator,
    str::FromStr,
};

fn main() {
    let mut io = io();

    let passengers = io.read();
    let stops = io.read();
    let delay: i64 = io.read();
    let boarding: i64 = io.read();
    let ds: Vec<i64> = {
        let differences: Vec<i64> = io.collect_n(stops);
        let mut results = vec![0i64; stops];
        results[0] = differences[0];
        for i in 1..stops {
            results[i] = results[i-1] + differences[i];
        }
        results
    };
    let ts: Vec<i64> = io
        .read_n(passengers)
        .map(|idx: usize| ds[idx - 1])
        .collect();

    // simulate that ts[start..start..num_ppl] take bus number `bus`
    let simulate = |start: usize, mut num_ppl: usize, bus: i64| {
        if start + num_ppl > passengers {
            return i64::MAX;
        }
        let mut guys = ts[start..start + num_ppl].to_vec();
        guys.sort();

        let mut t = bus * delay + boarding * guys.len() as i64;
        if let Some(last) = guys.last() {
            t += last;
        }

        for dudes in guys.chunk_by(|a, b| a == b) {
            t += num_ppl as i64 * boarding;
            num_ppl -= dudes.len();
            t += num_ppl as i64 * boarding;
        }
        t
    };

    let works = |deadline: i64| {
        let mut bus = 0;
        let mut start = 0;
        while start < passengers {
            let mut l = 0;
            let mut r = 1;
            while simulate(start,r,bus) <= deadline { 
                r *= 2; 
            }
            while r - l > 1 {
                let m = (r + l) / 2;
                if simulate(start, m, bus) <= deadline {
                    l = m;
                } else {
                    r = m;
                }
            }
            start = start + l;
            bus += 1;
            if l == 0 {
                return false;
            }
        }
        true
    };

    let mut l = 0;
    let mut r = passengers as i64 * delay + 2 * boarding + ds.last().unwrap();
    while r - l > 1 {
        let m = (r + l) / 2;
        if works(m) {
            r = m;
        } else {
            l = m;
        }
    }

    putln!(io, "{r}");
}

fn io() -> Io<impl Iterator<Item = &'static str>> {
    // Leaking the input lines is a bit wasteful but generally fine in a
    // competitive programming context and avoids having to deal with lifetimes
    // in the input reading.
    let input = io::stdin().lines().flat_map(|line| {
        line.expect("failed to read input line")
            .leak()
            .split_whitespace()
    });
    Io(input, BufWriter::new(io::stdout().lock()))
}

struct Io<I>(I, BufWriter<StdoutLock<'static>>);

#[allow(dead_code)]
impl<I: Iterator<Item = &'static str>> Io<I> {
    fn read_str(&mut self) -> &'static str {
        self.0.next().expect("unexpected end-of-file")
    }

    fn read<T: FromStr<Err: Debug>>(&mut self) -> T {
        self.read_str().parse().expect("failed to parse input")
    }

    fn read_n<T: FromStr<Err: Debug>>(&mut self, n: usize) -> impl Iterator<Item = T> + '_ {
        (0..n).map(move |_| self.read())
    }

    fn collect_n<T: FromStr<Err: Debug>, C: FromIterator<T>>(&mut self, n: usize) -> C {
        self.read_n(n).collect()
    }
}

#[macro_export]
macro_rules! putln {
    ($io:expr $(, $($args:tt)*)?) => {
        writeln!($io.1 $(, $($args)*)?).expect("failed to write output")
    };
}

#[macro_export]
macro_rules! put {
    ($io:expr, $($args:tt)*) => {
        write!($io.1, $($args)*).expect("failed to write output")
    };
}
