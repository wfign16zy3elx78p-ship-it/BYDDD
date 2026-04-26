const reveals = document.querySelectorAll('.reveal');
const io = new IntersectionObserver(
  (entries) => {
    entries.forEach((entry) => {
      if (entry.isIntersecting) entry.target.classList.add('visible');
    });
  },
  { threshold: 0.2 }
);
reveals.forEach((el) => io.observe(el));

const car = document.getElementById('carModel');
window.addEventListener('scroll', () => {
  const spin = (window.scrollY / 8) % 360;
  car.style.transform = `rotateY(${spin}deg)`;
});

document.querySelectorAll('.swatch').forEach((swatch) => {
  swatch.addEventListener('click', () => {
    document.documentElement.style.setProperty('--accent', swatch.dataset.color);
  });
});
