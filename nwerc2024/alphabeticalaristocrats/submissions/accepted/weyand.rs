use std::io;

fn main() {
    let mut names: Vec<_> = io::stdin()
        .lines()
        .skip(1)
        .filter_map(|l| l.ok())
        .collect();
    names.sort_by_cached_key(|name| {
        name.chars()
            .skip_while(|c| !c.is_ascii_uppercase())
            .collect::<String>()
    });

    for name in names {
        println!("{name}")
    }
}
