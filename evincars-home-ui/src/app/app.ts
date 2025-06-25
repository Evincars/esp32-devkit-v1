import { Component, ChangeDetectionStrategy } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { Observable } from "rxjs";
import { BreakpointObserver, Breakpoints } from "@angular/cdk/layout";
import { map, shareReplay } from "rxjs/operators";

@Component({
  selector: 'app-root',
  template: `
    <mat-sidenav-container class="sidenav-container">
      <mat-sidenav
        #drawer
        class="sidenav"
        fixedInViewport
        [attr.role]="(isHandset$ | async) ? 'dialog' : 'navigation'"
        [mode]="(isHandset$ | async) ? 'over' : 'side'"
        [opened]="(isHandset$ | async) === false"
      >
        <mat-toolbar>Menu</mat-toolbar>
        <mat-nav-list>
          <a mat-list-item routerLink="/">
            <mat-icon matListItemIcon class="menu-icon">dashboard</mat-icon>
            <div matListItemTitle>Přehled</div>
          </a>
          <a mat-list-item routerLink="/homeServices">
            <mat-icon matListItemIcon class="menu-icon">settings</mat-icon>
            <div matListItemTitle>Domácnost</div>
          </a>
          <a mat-list-item routerLink="/about">
            <mat-icon matListItemIcon class="menu-icon">info</mat-icon>
            <div matListItemTitle>O Aplikaci</div>
          </a>
        </mat-nav-list>
      </mat-sidenav>
        <mat-sidenav-content>
          <mat-toolbar color="primary">
            <button
              type="button"
              aria-label="Toggle sidenav"
              mat-icon-button
              (click)="drawer.toggle()"
            >
              <mat-icon aria-label="Side nav toggle icon">menu</mat-icon>
            </button>
            <span>LasakHouse IoT</span>
          </mat-toolbar>
          <div class="content-wrapper">
            <router-outlet></router-outlet>
          </div>
      </mat-sidenav-content>
    </mat-sidenav-container>
  `,
  styles: `
    .sidenav-container {
      height: 100%;
    }

    .sidenav {
      width: 200px;
    }

    .sidenav .mat-toolbar {
      background: inherit;
    }

    .mat-toolbar.mat-primary {
      position: sticky;
      top: 0;
      z-index: 1;
    }

    .menu-icon {
      color: gold !important;
    }

    .content-wrapper {
      padding: 20px;
    }
  `,
  imports: [RouterOutlet],
  changeDetection: ChangeDetectionStrategy.OnPush,
})
export class App {
  protected title = 'evincars-home-ui';
}
